# QCVT
A quick command line conversion tool to visualize different  
representations of some input data.  

Build the program and alias the binary as you feel appropriate.  
In my case I have aliased the binary as `cv` in the bashrc.  

## Use
Simply enter:
`{your alias name} [-b] {some number}`
Where `{some number}` is a float, int, or hex value (preceded by 0x).  
The `-b` option will additionally print the binary representation of  
your entry.  

Standard output will represent the entry as:
- float (decimal and hex representation)
- int (signed, unsigned, hex)

Binary output will show:
- float binary
- int binary
