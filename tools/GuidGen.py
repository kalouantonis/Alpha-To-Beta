#!/usr/bin/env python

import uuid
import sys

# Get name to generate hash for
try:
	(script, name) = sys.argv
except ValueError:
	print "No arguments passed.\n\tUsage: GuidGen.py <name>"
	sys.exit()

# Generate UUID using given name
guid = str(uuid.uuid3(uuid.NAMESPACE_OID, name))

# Output 1 byte hex identifier
print name + ": " + "0x" + guid[:8]
