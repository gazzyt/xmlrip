A very simple streaming XPath processor. I created this tool for querying XML files that were too large for building a DOM or loading into an editor. Grep and Less work OK until you want to extract multiline elements.
Xmlrip only support some very basic XPath features (basically only what I needed).

The full list of things you can do is:
* Find elements by name `/outer`
* Find elements at any depth `//inner`
* Find elements by path `/outer/inner` or `/outer//inner`
* Filter elements on specific attribute value `/outer/inner[@c="EP1234"]`
* Filter elements on attribute values beginning with a sequence of characters `/outer/inner[starts-with(@c,"EP")]`

Building
========

Linux
-----
Requires GCC, cmake and make installed:
	sudo apt-get install libxml2-dev gcc g++ make cmake

From the folder containing the checked out code do:
````
mkdir build
cd build
cmake ..
make
````

To run the tests:
	./testxmlrip/testxmlrip
	
To run the app:
	./xmlrip/xmlrip ../test3.xml '//outer'

Windows
-------
Use Visual Studio 2017 and use the "File > Open Folder" feature to open the checkout folder. VS will then run cmake for you.
Use the the drop down in the toolbar to select build target.
If you install the Google Test adapter then the IDE will discover and run the unit tests for you.
