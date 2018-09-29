#!env python
# Generate password hash
# See https://www.aychedee.com/2012/03/14/etc_shadow-password-hash-formats/
import crypt
import getpass
import numpy as np
import string

password = getpass.getpass()
salt_len = 16
salt = ''.join(
    np.random.choice(
        list(string.ascii_letters + string.digits), 
        salt_len
    )
)
prefix = '$6$'

shadow = crypt.crypt(password, prefix+salt)
print(shadow)
