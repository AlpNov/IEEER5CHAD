# invoke SourceDir generated makefile for main.pem4f
main.pem4f: .libraries,main.pem4f
.libraries,main.pem4f: package/cfg/main_pem4f.xdl
	$(MAKE) -f C:\Users\Christopher\Desktop\CCS_Code\embedded_Program\embedded_Program/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Christopher\Desktop\CCS_Code\embedded_Program\embedded_Program/src/makefile.libs clean

