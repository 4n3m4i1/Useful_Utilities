# KiCad 7 BOM / POS to JLC Format Tool
The standard KiCad 7 output for BOM (default option, no extra arguments), and position files (pcb -> fab output -> csv) are not quite right for JLC's PCBA service.  
This simple tool will produce revices files with correct headers, and delete extraneous columns. Row (component) deletions, and LCSC part numbers must still be entered manually. LCSC part numbers should be entered after running the tool as a column will be created for these in the BOM file.  
  
## Usage
Compile the program, and probably alias it so it's not a pain to use. Create BOM and POS outputs as you normally would, ensure these files are in some output directory you want new outputs to be created in. Run this program with the following options:  
- `-b, -B, -BOM, -bom {BOM FILENAME}.csv` to generate BOM
- `-p, -P, -POS, -pos {POS FILENAME}.csv` to generate POS
  
The tool can run both, or an individual file.