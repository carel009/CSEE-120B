# Test file for "lab6 ex.2"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

# Add tests below

# Test sequence from Start: PORTB: 0x01
test "PORTB: 0x01, state: LED1"
set state = Start
continue .3
expectPORTB 0x01
expect state LED1
checkResult

# Test sequence from LED1: PORTB: 0x02
test "PORTB: 0x02, state: LED2"
set state = LED1
continue .3
expectPORTB 0x02
expect state LED2
checkResult

# Test sequence from LED2: PORTB: 0x04
test "PORTB: 0x04, state: LED3"
set state = LED2
continue .3
expectPORTB 0x04
expect state LED3
checkResult

# Test sequence from LED3: PORTB: 0x02
test "PORTB: 0x02, state: LED_2"
set state = LED3
continue .3
expectPORTB 0x02
expect state LED_2
checkResult

# Test sequence from LED_2: PORTB: 0x02
test "PINA: 0x01 => PORTB: 0x02, state: STOP"
set state = LED_2
setPINA 0xFE
continue .3
expectPORTB 0x02
expect state STOP
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
