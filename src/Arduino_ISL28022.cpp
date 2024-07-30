#include "Arduino_ISL28022.h"

/* _______________________________________________________DEFAULT CONSTRUCTOR */
ISL28022Class::ISL28022Class() : _wire(Wire), 
                                 slave_address(DEFAULT_SLAVE_ADDRESS) {
}

/* _______________________________________________________________CONSTRUCTOR */
ISL28022Class::ISL28022Class(TwoWire &w) : _wire(w), 
                                           slave_address(DEFAULT_SLAVE_ADDRESS) {
}

/* _______________________________________________________________CONSTRUCTOR */
ISL28022Class::ISL28022Class(uint8_t a) : _wire(Wire), 
                                          slave_address(a){
}
 
/* _______________________________________________________________CONSTRUCTOR */ 
ISL28022Class::ISL28022Class(TwoWire &w, uint8_t a) : _wire(w), 
                                                      slave_address(a){
}

/* _______________________________________________________________DE-STRUCTOR */ 
ISL28022Class::~ISL28022Class() {}