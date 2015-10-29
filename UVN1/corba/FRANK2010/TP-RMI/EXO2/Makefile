JAVAC           = javac
RMIC		= rmic


.SUFFIXES:
.SUFFIXES:	.java .class 
.SUFFIXES:	.java _Stub.class

.java.class:
	$(JAVAC)  $<

.java_Stub.class:
	$(RMIC)   $*


#####################################################


CLASSES    = Compte.java Client.java MyHostName.java
INTERFACES = CompteServeur.java


all:  class rmic


rmic:	$(INTERFACES:.java=_Stub.class)


class:	$(CLASSES:.java=.class) 

	
clean:
	rm -rf *.class *.bak *~ core




