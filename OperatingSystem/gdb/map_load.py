import gdb

def is_object_file_line(line):
    return line.lstrip().startswith('.text ') and line.find('obj/') != -1


def extract_load_address(line):
    start_index = line.index('0x')
    end_index = line.index(' ', start_index)
    return line[start_index:end_index].strip()


def extract_object_filename(line):
    index = line.find('obj/')
    return line[index:].strip()


def map_load(filename):
    m = {}

    with open(filename, 'r') as map_file:
        for line in map_file.readlines():
            if not is_object_file_line(line):
                continue

            load_address = extract_load_address(line)
            object_filename = extract_object_filename(line)
            m[object_filename] = load_address

    return m

class LoadLinkerMapCommand(gdb.Command):
    """The right version for add-symbol-file"""

    def __init__(self):
        super(LoadLinkerMapCommand, self).__init__("map-load", gdb.COMMAND_NONE, gdb.COMPLETE_FILENAME)
        self.dont_repeat()

    def invoke(self, arg, from_tty):
        argv = gdb.string_to_argv(arg)
        filename = argv[0]

        for object_file, load_address in map_load(filename).iteritems():
            cmd = "add-symbol-file {object_file} {load_address}".\
                format(object_file=object_file, load_address=load_address)
            gdb.execute(cmd)

LoadLinkerMapCommand()