program main

  use smartredis_client, only : client_type

  implicit none

  type(client_type) :: client

  call client%initialize(.FALSE.)

end program main
