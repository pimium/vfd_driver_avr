
#ifndef VFD_INTERNAL
#define VFD_INTERNAL

#define MESSAGE_LENGTH 8
#define NUMBER_OF_CHARACTER 7
#define NUMBER_OF_REGISTER 4

// States
void vfd_states_start_write_byte(void);
void vfd_states_set_srclr(void);
void vfd_states_set_clk(void);
void vfd_states_clear_clk(void);
void vfd_states_set_word(void);
void vfd_states_set_rclK(void);
#endif
