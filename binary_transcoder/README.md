# Apollo Binary Transcoder
Simple program to convert binary file output of virtualagc into form for loading into embedded system memory.

Compile with `make`

Run `./build/transcoder <source binary file> <destination binary file>`  
where the source file is produced by virtualagc (or other source of raw AGC binary) and destination file is the file to be loaded into embedded system memory.
