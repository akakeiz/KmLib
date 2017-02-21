import uuid
import os


def Generate64BitUuid():
    return uuid.uuid1().int >> 64

def TryMakeDir( path ):
    if not os.path.isdir( path ):
        os.makedirs( path )

