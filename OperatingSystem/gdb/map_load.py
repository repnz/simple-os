try:
    import gdb
    run_inside_gdb = True
except ImportError:
    import sys
    import json
    run_inside_gdb = False

from collections import defaultdict

load_sections = [
    '.text',
    '.bss',
    '.rodata',
    '.data'
]

def is_object_file_line(line):
    return any(line.startswith(section + ' ') for section in load_sections) and line.find('obj/') != -1


def extract_load_address(line):
    start_index = line.index('0x')
    end_index = line.index(' ', start_index)
    return line[start_index:end_index]


def extract_object_filename(line):
    index = line.find('obj/')
    return line[index:]

def extract_section_name(line):
    return line[:line.index(' ')]

def map_load(filename):
    m = defaultdict(dict)

    with open(filename, 'r') as map_file:
        for line in map_file.readlines():
            line = line.strip()

            if not is_object_file_line(line):
                continue

            load_address = extract_load_address(line)
            object_filename = extract_object_filename(line)
            section_name = extract_section_name(line)
            
            m[object_filename][section_name] = load_address

    return m

def create_add_command(object_file, sections):
    cmd = "add-symbol-file {object_file} {text} -readnow".format(object_file=object_file, text=sections['.text'])
    del sections['.text']
    
    for section_name, load_address in sections.iteritems():
        cmd += ' -s {section} {address}'.format(section=section_name, address=load_address)

    return cmd

def main():
    map_filename = sys.argv[1]
    linker_map = map_load(map_filename)
    print json.dumps(linker_map, sort_keys=True, indent=4)    

if run_inside_gdb:
    class LoadLinkerMapCommand(gdb.Command):
        """The right version for add-symbol-file"""

        def __init__(self):
            super(LoadLinkerMapCommand, self).__init__("map-load", gdb.COMMAND_NONE, gdb.COMPLETE_FILENAME)
            self.dont_repeat()

        def invoke(self, arg, from_tty):
            argv = gdb.string_to_argv(arg)
            map_filename = argv[0]

            for object_file, sections in map_load(map_filename).iteritems():
                cmd = create_add_command(object_file, sections)
                gdb.execute(cmd)

    LoadLinkerMapCommand()

elif __name__ == '__main__':
    main()