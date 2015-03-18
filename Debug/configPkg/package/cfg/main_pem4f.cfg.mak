# invoke SourceDir generated makefile for main.pem4f
main.pem4f: .libraries,main.pem4f
.libraries,main.pem4f: package/cfg/main_pem4f.xdl
	$(MAKE) -f D:\DOCUME~1\School\SRDESI~1\IEEER5CHAD/src/makefile.libs

clean::
	$(MAKE) -f D:\DOCUME~1\School\SRDESI~1\IEEER5CHAD/src/makefile.libs clean

