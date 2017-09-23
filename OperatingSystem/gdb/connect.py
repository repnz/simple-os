import gdb

class RemoteConnectCommand(gdb.Command):
    def __init__(self):
        super(RemoteConnectCommand, self).__init__("connect", gdb.COMMAND_NONE, gdb.COMPLETE_FILENAME)
        self.dont_repeat()

    def invoke(self, arg, from_tty):
        argv = gdb.string_to_argv(arg)
        ip = argv[0]
		
        port = 1234 if len(argv) < 2 else argv[1]

        gdb.execute("target remote {ip}:{port}".format(ip=ip, port=port))

RemoteConnectCommand()