make:
	mkfifo chat
	gcc write.c -o Write 
	gcc read.c -o Read 
	sudo gnome-terminal -x sh -c "sudo ./Read" 
	sudo ./Write 
