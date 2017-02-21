import uuid
import os

# Return 64Bit UUID
def Generate64BitUuid():
    return uuid.uuid1().int >> 64

# Make directory if not exits
def TryMakeDir( path ):
    if not os.path.isdir( path ):
        os.makedirs( path )

