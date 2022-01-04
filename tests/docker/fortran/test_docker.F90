program main

    use smartredis_client, only : client_type

    implicit none

#include "enum_fortran.inc"

    integer(kind=enum_kind) :: result
    type(client_type) :: client
    integer, parameter :: dim1 = 10
    real(kind=8), dimension(dim1) :: tensor

    result = client%initialize(.FALSE.)
    if (result .ne. SRNoError) stop

    call random_number(tensor)

    result = client%put_tensor("fortran_docker_tensor", tensor, shape(tensor))
    if (result .ne. SRNoError) stop

end program main
