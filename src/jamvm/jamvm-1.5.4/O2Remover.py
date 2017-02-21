file_paths = []

file_paths.append("Makefile")
file_paths.append("lib/Makefile")
file_paths.append("lib/gnu/Makefile")
file_paths.append("lib/gnu/classpath/Makefile")
file_paths.append("lib/jamvm/Makefile") 
file_paths.append("lib/jamvm/java/Makefile")
file_paths.append("lib/jamvm/java/lang/Makefile")
file_paths.append("lib/java/Makefile")
file_paths.append("lib/java/security/Makefile")
file_paths.append("lib/java/lang/Makefile")
file_paths.append("lib/java/lang/reflect/Makefile")
file_paths.append("lib/sun/Makefile")
file_paths.append("lib/sun/reflect/Makefile")
file_paths.append("lib/sun/reflect/annotation/Makefile")
file_paths.append("src/Makefile")
file_paths.append("src/arch/Makefile")
file_paths.append("src/interp/Makefile")
file_paths.append("src/interp/engine/Makefile")
file_paths.append("src/os/Makefile")
file_paths.append("src/os/linux/Makefile")
file_paths.append("src/os/linux/x86_64/Makefile")

find_replace = [
(u"CCASFLAGS = -g -O2", u"CCASFLAGS = -g -O0"),
(u"CFLAGS = -g -O2", u"CFLAGS = -g -O0"),
(u"CXXFLAGS = -g -O2", u"CXXFLAGS = -g -O0"),
]

for file_path in file_paths:
    INPUT_FILE = open(file_path, "rb")
    file_content = unicode(INPUT_FILE.read(), "utf-8")
    INPUT_FILE.close()
    
    for couple in find_replace:
        out_text = file_content.replace(couple[0], couple[1])
        file_content = out_text
        
    OUTPUT_FILE = open(file_path, "wb")
    OUTPUT_FILE.write(out_text.encode("utf-8"))
    OUTPUT_FILE.close()
