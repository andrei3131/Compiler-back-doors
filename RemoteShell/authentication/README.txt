The following directories contain html formatted line coverage
for common gpg2 commands:

------------------------------------------------------------------
     Directory               |          Command                  |
------------------------------------------------------------------   
  	                     |
  FullGenKeyCov              |  gpg2 --full-gen-key (Creates a key pair. I assume only RSA is used.)
  ListPublicKeysCov          |  gpg2 --list-keys
  ListPrivateKeysCov         |  gpg2 --list-secret-keys
  ExportPublicKeyToFileCov   |  gpg2 --output <destination_public.key> --armor --export user_id (Export the public key)
  ImportPublicKeyCov         |  gpg2 --import public.key (Import the key on the server from file public.key)
  EncryptWithPublicKeyCov    |	gpg2 --recipient user_id --encrypt <plain_text_msg_file> (The result is an <encrypted_message_file>. Encrypted using public key.)
  DecryptWithPrivateKeyCov   |  gpg2 --output <plain_text_msg_file> --decrypt <encrypted_message_file> (The result is a <plain_text_msg_file>. Decrypted using private key.)
