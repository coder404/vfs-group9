../bin/finalout.out : ../bin/test.o ../bin/vfs_funcs.o ../bin/nary_tree.o ../bin/vfs_opns.o
	gcc ../bin/test.o ../bin/vfs_funcs.o ../bin/nary_tree.o ../bin/vfs_opns.o -o ../bin/finalout.out -lm
	
../bin/test.o : ../test/test.c
	gcc -c ../test/test.c -o ../bin/test.o
	
../bin/vfs_opns.o : ../src/VFS_Operations.c 
	gcc -c ../src/VFS_Operations.c -o ../bin/vfs_opns.o
	
../bin/vfs_funcs.o : ../src/VFS_Functions.c  ../src/Nary_Tree_Creation.c 
	gcc -c ../src/VFS_Functions.c -o ../bin/vfs_funcs.o -lm
	
../bin/nary_tree.o : ../src/Nary_Tree_Creation.c 
	gcc -c ../src/Nary_Tree_Creation.c -o ../bin/nary_tree.o 

