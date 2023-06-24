import os

cwd = os.getcwd()
os.chdir(f"{cwd}\\src\\assets\\ppm")

for i in os.listdir():
    print(f"Processing {i.upper()}")
    os.system(f"python.exe {cwd}\\src\\ppm2ssg\\ppm2ssg_vga256.py {cwd}\\src\\assets\\ppm\\{i} {cwd}\\src\\assets\\ssg\\{i.split('.')[0].upper()}.SSG")    
    