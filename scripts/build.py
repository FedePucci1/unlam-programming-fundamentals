"""Compile two C programs and two standalone solution objects; Windows also builds the clock."""
from pathlib import Path
import os
import subprocess

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'build'
OUT.mkdir(exist_ok=True)
cc = os.environ.get('CC', 'gcc')
cxx = os.environ.get('CXX', 'g++')
flags = ['-std=c11', '-Wall', '-Wextra', '-fexec-charset=ISO-8859-1']
for name in ['bank-accounts', 'string-replacement']:
    directory = ROOT / 'exercises' / name
    target = OUT / (name + ('.exe' if os.name == 'nt' else ''))
    subprocess.run([cc, *flags, *map(str, sorted(directory.glob('*.c'))), '-o', str(target)], check=True)
    print(f'Built {name}', flush=True)
for name in ['text-and-matrices', 'encoding-and-records']:
    directory = ROOT / 'exercises' / name
    subprocess.run([cc, *flags, '-c', str(directory / 'funciones.c'), '-o', str(OUT / (name + '.o'))], check=True)
    print(f'Compiled object {name} (course reference library not included)', flush=True)
if os.name == 'nt':
    directory = ROOT / 'exercises' / 'time-of-day'
    subprocess.run([cxx, '-std=c++11', '-Wall', '-Wextra', *map(str, sorted(directory.glob('*.cpp'))), '-o', str(OUT / 'time-of-day.exe')], check=True)
    print('Built time-of-day (Windows console)', flush=True)
