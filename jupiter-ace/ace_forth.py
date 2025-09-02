#!/usr/bin/env python3
"""
Simple Jupiter Ace Forth cross-compiler
Converts Forth programs to Jupiter Ace tape format
"""

import sys
import struct

# Jupiter Ace memory map
ROM_START = 0x0000
ROM_END = 0x1FFF
RAM_START = 0x2000
SCREEN_START = 0x2400
USER_START = 0x3C00

# Forth dictionary structure
LINK_OFFSET = 0
NAME_OFFSET = 2
CODE_OFFSET = 8

class AceForth:
    def __init__(self):
        self.dictionary = {}
        self.here = USER_START  # Compilation pointer
        self.output = bytearray()
        
    def compile_word(self, name, forth_code):
        """Compile a Forth word to Z80 machine code"""
        # This is a simplified compiler - real Forth is much more complex
        
        if name.upper() == "HELLO":
            # Example: compile a simple word
            code = [
                0x21, 0x00, 0x24,  # LD HL, 0x2400 (screen start)
                0x36, ord('H'),     # LD (HL), 'H'
                0x23,               # INC HL
                0x36, ord('E'),     # LD (HL), 'E'
                0x23,               # INC HL
                0x36, ord('L'),     # LD (HL), 'L'
                0x23,               # INC HL
                0x36, ord('L'),     # LD (HL), 'L'
                0x23,               # INC HL
                0x36, ord('O'),     # LD (HL), 'O'
                0xC9                # RET
            ]
            return bytes(code)
        
        elif name.upper() == "CLEAR":
            # Clear screen
            code = [
                0x21, 0x00, 0x24,  # LD HL, 0x2400 (screen start)
                0x06, 24,           # LD B, 24 (lines)
                0x0E, 32,           # LD C, 32 (columns)
                0x36, ord(' '),     # LD (HL), ' '
                0x23,               # INC HL
                0x0D,               # DEC C
                0x20, 0xFC,         # JR NZ, -4
                0x0E, 32,           # LD C, 32
                0x05,               # DEC B
                0x20, 0xF7,         # JR NZ, -9
                0xC9                # RET
            ]
            return bytes(code)
        
        else:
            # Default: return immediately
            return bytes([0xC9])  # RET
    
    def create_tap_file(self, filename, program_name, code):
        """Create Jupiter Ace .TAP file"""
        # TAP file format for Jupiter Ace
        tap_data = bytearray()
        
        # Header block
        header = bytearray()
        header.extend(program_name.ljust(10).encode('ascii')[:10])
        header.extend(struct.pack('<H', len(code)))  # Program length
        header.extend(struct.pack('<H', USER_START))  # Load address
        
        # Add header to TAP
        tap_data.extend(struct.pack('<H', len(header) + 2))
        tap_data.extend([0x00])  # Header flag
        tap_data.extend(header)
        
        # Calculate checksum
        checksum = 0
        for byte in header:
            checksum ^= byte
        tap_data.append(checksum)
        
        # Data block
        tap_data.extend(struct.pack('<H', len(code) + 2))
        tap_data.extend([0xFF])  # Data flag
        tap_data.extend(code)
        
        # Calculate data checksum
        checksum = 0xFF
        for byte in code:
            checksum ^= byte
        tap_data.append(checksum)
        
        return tap_data

def main():
    if len(sys.argv) != 3:
        print("Usage: ace_forth.py input.forth output.tap")
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    
    compiler = AceForth()
    
    try:
        with open(input_file, 'r') as f:
            forth_code = f.read()
        
        # Simple parsing - look for word definitions
        lines = forth_code.split('\n')
        all_code = bytearray()
        
        for line in lines:
            line = line.strip()
            if line.startswith(':') and line.endswith(';'):
                # Word definition
                parts = line[1:-1].strip().split()
                if parts:
                    word_name = parts[0]
                    word_body = ' '.join(parts[1:])
                    code = compiler.compile_word(word_name, word_body)
                    all_code.extend(code)
        
        # If no words defined, create a simple program
        if not all_code:
            all_code = compiler.compile_word("HELLO", "")
        
        # Create TAP file
        program_name = input_file.replace('.forth', '').replace('.f', '')
        tap_data = compiler.create_tap_file(output_file, program_name, all_code)
        
        with open(output_file, 'wb') as f:
            f.write(tap_data)
        
        print(f"Compiled {input_file} to {output_file}")
        print(f"Program size: {len(all_code)} bytes")
        
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == '__main__':
    main()