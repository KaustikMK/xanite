#ifndef DRIVER_RETURN_CODE_H
#define DRIVER_RETURN_CODE_H

typedef enum  {
    DRIVER_OP_SUCCESS        =  0, /**< in cases where an int is
                                    returned, like cdio_set_speed,
                                    more the negative return codes are
                                    for errors and the positive ones
                                    for success. */
    DRIVER_OP_ERROR          = -1, /**< operation returned an error */
    DRIVER_OP_UNSUPPORTED    = -2, /**< returned when a particular driver
                                      doesn't support a particular operation.
                                      For example an image driver which doesn't
                                      really "eject" a CD.
                                   */
    DRIVER_OP_UNINIT         = -3, /**< returned when a particular driver
                                      hasn't been initialized or a null
                                      pointer has been passed.
                                   */
    DRIVER_OP_NOT_PERMITTED  = -4, /**< Operation not permitted.
                                      For example might be a permission
                                      problem.
                                   */
    DRIVER_OP_BAD_PARAMETER  = -5, /**< Bad parameter passed  */
    DRIVER_OP_BAD_POINTER    = -6, /**< Bad pointer to memory area  */
    DRIVER_OP_NO_DRIVER      = -7, /**< Operation called on a driver
                                      not available on this OS  */
    DRIVER_OP_MMC_SENSE_DATA = -8, /**< MMC operation returned sense data,
                                      but no other error above recorded. */
} driver_return_code_t;

#endif // DRIVER_RETURN_CODE_H