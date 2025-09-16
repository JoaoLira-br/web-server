# libeom
#
# Makefile for libeom - provides options for creating a static library out of all or part of libeom
#
# 2021-02-12
# Eric Meehan

###############################################################################
# MARK: ALL
###############################################################################

# Create top level static library and all sub-libraries
all: Main DataStructures Networking Systems test

###############################################################################
# MARK: MAIN
###############################################################################

Main: DataStructuresSub NetworkingSub 
	ar rcs libeom.a Node.o LinkedList.o Queue.o BinarySearchTree.o Entry.o Dictionary.o Server.o  HTTPRequest.o HTTPServer.o ThreadPool.o

###############################################################################
# MARK: DATA STRUCTURES
###############################################################################

DataStructures: DataStructuresSub
	ar rcs DataStructures/DataStructures.a Node.o LinkedList.o Queue.o BinarySearchTree.o Entry.o Dictionary.o
	
DataStructuresSub: Node LinkedList Queue BinarySearchTree Entry Dictionary

Node:
	gcc -c DataStructures/Common/Node.c

LinkedList:
	gcc -c DataStructures/Lists/LinkedList.c

Queue:
	gcc -c DataStructures/Lists/Queue.c
	
BinarySearchTree:
	gcc -c DataStructures/Trees/BinarySearchTree.c

Entry:
	gcc -c DataStructures/Dictionary/Entry.c

Dictionary:
	gcc -c DataStructures/Dictionary/Dictionary.c
	
###############################################################################
# MARK: NETWORKING
###############################################################################

Networking: NetworkingSub
	ar rcs Networking/Networking.a Server.o  HTTPRequest.o HTTPServer.o  LinkedList.o Queue.o BinarySearchTree.o Entry.o Dictionary.o ThreadPool.o 

NetworkingSub: DataStructuresSub SystemsSub Server HTTPRequest HTTPServer 

Server:
	gcc -c Networking/Nodes/Server.c

HTTPServer: 
	gcc -c Networking/Nodes/HTTPServer.c

HTTPRequest:
	gcc -c Networking/Protocols/HTTPRequest.c


###############################################################################
# MARK: Systems
###############################################################################

# Creates the systems library
Systems: SystemsSub
	ar rcs Systems/System.a ThreadPool.o 

# Sub components of the systems library
SystemsSub: ThreadPool 

ThreadPool:
	gcc -c Systems/ThreadPool.c

###############################################################################
# MARK: TEST
###############################################################################
test: test.o
	gcc -o test test.o -L. -leom DataStructures/DataStructures.a Systems/System.a Networking/Networking.a 

test.o: testing/main.c
	gcc -c testing/main.c -o test.o
		

###############################################################################
# MARK: CLEAN
###############################################################################

clean:
	rm *.o
	rm test
