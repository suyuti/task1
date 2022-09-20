# JSON - TLV Converter

## What is JSON-TLV Convereter

This converter reads JSON object lines from a file or stream then extracts keys and store values in TLV form in a file.

## What is JSON
JSON is a data definition specification. Data structured as key value pairs. Nested data objects are valid.

## What is TLV

TLV is an encoding algorithm. It is used on communication and specially payment systems commonly. Like JSON it can be complex or nested structured.
Each object defined in Tag, Length and Value parts.
Tag defines object identity or type.
Length part keeps length of payload the value part.
Value is data itself. It can be any format, any encoding. 
Tag and Length parts have known length. It can be dynamic for advanced usage. Briefly mentioned below.


Example
|Tag|Length|Value|
|---|---|---|
| 0x02|0x03|0x31 0x32 0x33



## Development Environment


Development environment is defined as a Docker container. 
You have to build Docker image first. Then all developers will have same environment and dependencies.


To build docker image run this command

`docker build -t nxlog/nxlog_build:0.1 .`

or 

`/build.sh`

It will build an image named **nxlog**

This image has required development environment and dependencies. It is Debian OS.

After docker image built, the image will be run.

`docker run -it --rm --name=nxlog \
    --mount type=bind,source=${PWD}/src,target=/src \
	nxlog/nxlog_build:0.1 \
	bash`

or

`/run.sh`

You are in docker container now.

The source folder shared between your host computer and docker container. So you can play with them.


## Build

Build is done by CMake
There are several different targets in CMake definition.

First of all create a build folder in **/src**

`mkdir build`

`cd build`

`cmake ..`

`make`

It will build the project for all targets, application and test runners.

You can run the application now

`./packer`


## Test

GoogleTest is used for testing purposes.
Tests are defined in **packerTest.cpp**
You can add more tests as seperated file. GoogleTest builder will find them.

Tests can be run as

`ctest`

after project build.


## Input File


Input file has simple JSON objects each line.
Input file is a text file.
JSON objects have primitive types of features, only integer, boolean and string.
Input file can be any arbitrary length. The file is handled as stream.
Each line must be shorter than 1024 bytes length.

## Output File

Output file contains only TLV ojects array.
Output file is in binary format.
TLV objects are regular objects those do not have sub-objects.

## Important Notes

- All incoming lines are accepted as legal JSON object

- All JSON objects have only primitive data types such as integer, boolean and string

- JSON object in input file line must be shorter than 1024 bytes length. It can be longer or dynamic but line buffer is defined 1024 bytes long for this task.

- All keys in whole input file accepted as unique. Keys are not repeated among lines. Repeating keys in a line are not valid regarding to JSON rules though. I mean keys will not repeat among lines. Since it is not mentioned in requirement, it is assumed.

`
{"KEY1":"hello", "key2":"world"}<LF>
{"KEY1":"hello-again", "key3":"mars"}
`

- Since all keys are unique and converted to sequential integer number, key is not stored in TLV. Sequential integer number means index of TLV array though. It is explained below.
- Key dictionary is not stored seperated. It could be but not mentioned in requirement document. It can be stored as reference index for TLV array.


## Notes for developers

Incoming data is in (simple) JSON objects. Incoming data is parsed and then extracted keys are stored in a tree structure separated. It may be used as index though.

Value parts are stored in TLV format.
TLV is a special encoding structure commonly used in telecommunication and payment system.
TVL data structure has three part.

Since the keys of JSON objects are indexed sequentially, TLV objects are also stored sequentially. The key of the first object is 1. Subsequent objects also receive ascending numbers, respectively.
That's why I didn't keep the key of the object in TLV.
But access to objects in TLV array is sequential. 
It has **O(n)** complexity.

To improve this, access information can be stored in the index, the key dictionary.
The key of the object can be kept in the TLV. However, this will be the same as the sequence number of the TLV object. So there is no need to keep the object key.
Also, if we want to keep the index of the object as Tag in TLV, the Tag part will need to be larger than one byte for large numbers.
If we keep the type information as a tag, only 1 byte is enough.

### Length
Length information is kept as 1 byte. 1 byte length information means that there can be a maximum of 255 bytes of information. But there may be longer data. For this situation, the Length information can be kept in two or more bytes.
In this case, it can be in the form of TLLV.
The largest significant bit of the length information can be defined as one or more bytes of the length information. For example, if a data is 200 bytes long, the Length information will be 2 bytes. The highest significant bit of the first byte will be 1. This indicates that there is one more byte in the length information.
However, this is not coded. It can only be used in advanced cases.

### Value

For this task, only primitive data is assumed as value. Only **integer**, **string** and **boolean**.
However, in reality, there may be nested structures or complex structures.
These all have been ignored.

### Integer

Integer values ​​can be stored in several different forms.

**BCD**, **ASCII**, or **Binary**.

In BCD form, the integer value can be stored as binary digits.

For example 123 is encoded in BCD as **0x01 0x23**
It needs an average of half the number of steps.

In **ASCII** form, each digit of the integer value is stored as a character.

For example 123 will be **0x31 0x32 0x33**

Obviously it needs as much space as the number of digits.

In binary form, the integer value is stored as binary. A 32-bit integer value needs 4 bytes of space. It is stored as Little-Endian or Big-Endian according to the system. Numbers that exceed 32 bits will overflow.

For example 123 will be **0x7B 0x00 0x00 0x00**

In this task, numerical values ​​are stored in Binary form. To store in BCD form, Integer-BCD conversions must be made that is not implemented.

### String
String values ​​are stored directly as ASCII.
Unicode values ​​are also acceptable.

For example "Hello" will be **'H' 'e' 'l' 'l' 'o'**

### Boolean
Boolean values ​​can be defined as **0x00** or **0x01** in the value part.

For example, a boolean value can be defined in the TLV structure as follows.

`#define TAG_BOOLEAN 0x04`

Whole TLV structure for **True** value

`0x04 0x01 0x01`

Whole TLV structure for **False** value

`0x04 0x01 0x00`

There are only two known values ​​for boolean values. Either true or false.

We can define these known values ​​for space optimization only as a **TAG**. 

There is no need to store the Length and Value information.

`TAG 0x05 for true value`

`TAG 0x06 for false value`

can be defined.

However, in this case, the TLV parser should recognize these special Boolean tags and not need for the Length and Value sections.

In this case, the TLV parser will not be portable. External systems cannot decode the TLV structure.
However, customized tags can be used for internal use.

It can be used as only for space optimization. It is not recommended. The benefit is only 2 bytes for 3 bytes.

`0x04 0x01 0x01`

will be

`0x05`

Also many different optimization can be implemented but they have costs.

## Author

Mehmnet Suyuti Dindar

mehmet.dindar@gmail.com