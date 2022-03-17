
all: grafiG oc

clean:
	$(RM) grafi/*.class
	$(RM) ./*.class

grafiG: grafi/arco_G.java grafi/grafo_G.java
	javac grafi/arco_G.java
	javac grafi/grafo_G.java
	javac grafi/vertice_G.java

app: application.java grafiG
	javac application.java

run_app: app
	java application input.txt correct.txt

oc: oc.java grafiG
	javac oc.java

run: oc
	ruby run-tests.rb "java oc"
