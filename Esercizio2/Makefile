
all: Edit_Distance CorrectionTextApp

clean:
	$(RM) ./*.class
	$(RM) Distance/*.class
	$(RM) test/*.class

Edit_Distance:
	javac Distance/Edit_Distance.java 

test: Edit_Distance
	javac -cp Resources/Java/JUnit/junit-4.12.jar:/Resources/Java/JUnit/hamcrest-core-1.3.jar:./ test/Edit_Distance_test.java
	javac -cp Resources/Java/JUnit/junit-4.12.jar:/Resources/Java/JUnit/hamcrest-core-1.3.jar:./ test/Edit_Distance_test_Run.java

runTest: test
	java -cp Resources/Java/JUnit/hamcrest-core-1.3.jar:Resources/Java/JUnit/junit-4.12.jar:./ test/Edit_Distance_test_Run

CorrectionTextApp:
	javac CorrectionTextApp.java

run: CorrectionTextApp Edit_Distance
	java CorrectionTextApp dictionary.txt correctme.txt
