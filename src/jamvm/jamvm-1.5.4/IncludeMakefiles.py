file_paths = []

file_paths.append("src/Makefile")
file_paths.append("src/interp/engine/Makefile")

find_replace = [
(u"CFLAGS = -g -O0", u"CFLAGS = -g -O0 -std=gnu99"),
(u"LIBS = -lffi -lz -ldl -lm -lpthread", u"LIBS = -lffi -lz -ldl -lm -lpthread -lpmemobj -lpmem"),
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
