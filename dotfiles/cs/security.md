# HMAC (Hash Based Message Authentication Code) の作り方
$ echo -n 'YourMessage' | openssl dgst -sha256 -hmac 'SecretKey'
8aff2951003c218bd26ee43c99e30527a0c30e06042008a60935ef1ab28891ec


