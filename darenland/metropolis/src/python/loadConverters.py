import string, sys

def loadConverters(src, dest):
	"""
	Loads the converter registration from the source file to the
	boost python module found in the dest file.
	"""
	src_file = open(src, 'r')
	src_text = src_file.read()
	src_file.close()
	dest_file = open(dest, 'r')
	in_text = dest_file.read()
	dest_file.close()
	start = string.rfind(in_text, 'BOOST_PYTHON_MODULE')
	#print start
	if start:
		index = string.find(in_text, '{', start)
		index += 1
		out_text = in_text[:index] + '\n' + '\t' + src_text + in_text[index:]
		#print out_text
		dest_file = open(dest, 'w')
		dest_file.write(out_text)

if len(sys.argv) == 3:
	loadConverters(sys.argv[1], sys.argv[2])
else:
	print '[ERR] Usage: loadConverters.py src dest'
