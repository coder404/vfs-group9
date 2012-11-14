../bin/vfsdriver : ../bin/test.o ../bin/vfs_funcs.o ../bin/nary_tree.o ../bin/bst_tree.o ../bin/vfs_opns.o ../bin/hash_table.o
	gcc ../bin/test.o ../bin/vfs_funcs.o ../bin/nary_tree.o ../bin/bst_tree.o ../bin/vfs_opns.o ../bin/hash_table.o -o ../bin/vfsdriver -lm
	
../bin/test.o : ../test/vfsdriver.c ../src/Nary_Tree_Creation.c ../src/Binary_Tree_Creation.c 
	gcc -c ../test/vfsdriver.c -o ../bin/test.o

../bin/vfs_opns.o : ../src/VFS_Operations.c
	gcc -c ../src/VFS_Operations.c -o ../bin/vfs_opns.o
	
../bin/vfs_funcs.o : ../src/VFS_Functions.c  ../src/Nary_Tree_Creation.c ../src/Binary_Tree_Creation.c 
	gcc -c ../src/VFS_Functions.c -o ../bin/vfs_funcs.o -lm
	
../bin/hash_table.o : ../src/Hash_Table_Creation.c
	gcc -c ../src/Hash_Table_Creation.c -o ../bin/hash_table.o
	
../bin/bst_tree.o : ../src/Binary_Tree_Creation.c
	gcc -c ../src/Binary_Tree_Creation.c -o ../bin/bst_tree.o 

../bin/nary_tree.o : ../src/Nary_Tree_Creation.c 
	gcc -c ../src/Nary_Tree_Creation.c -o ../bin/nary_tree.o
	 


