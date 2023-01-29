# Parser
This is a custom parser developed to read and write files in a custom way that is used for other projects of this author.

## Structure
### Text-based File
The first line should contain the name of the data contained, the second line should contain the attributes of the file, such as: length of the data, type of data and how many of them are inside.

#### Example:
> Problem data
>
> 3  11  2
>
> 1.0
>
> 2.0
> 
> 3.0
>
> 4.0
> 
> 5.0
> 
> 6.0

This is how two (2) vectors of three (3) elements of type double (11) would be represented inside the file.
