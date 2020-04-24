# Test file for "lab5 ex.3"


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

# Test sequence from Start: !A0, A0, !A0 => PORTB: 0x01
test "PINA: 0x00, 0x01, 0x00 => PORTB: 0x01, state: R1"
set state = Start
setPINA 0x00
continue 2
setPINA 0x01
continue 2 
setPINA 0x00
continue 2
expectPORTB 0x01
expect state R1
checkResult

# Test sequence from R1: !A0, A0, !A0 => PORTB: 0x03
test "PINA: 0x00, 0x01, 0x00 => PORTB: 0x03, state: R2"
set state = R1
setPINA 0x00
continue 2
setPINA 0x01
continue 2 
setPINA 0x00
continue 2
expectPORTB 0x03
expect state R2
checkResult

# Test sequence from R2: !A0, A0, !A0 => PORTB: 0x07
test "PINA: 0x00, 0x01, 0x00 => PORTB: 0x03, state: R3"
set state = R2
setPINA 0x00
continue 2
setPINA 0x01
continue 2 
setPINA 0x00
continue 2
expectPORTB 0x07
expect state R3
checkResult

# Test sequence from R3: !A0, A0, !A0 => PORTB: 0x0F
test "PINA: 0x00, 0x01, 0x00 => PORTB: 0x0F, state: R4"
set state = R3
setPINA 0x00
continue 2
setPINA 0x01
continue 2 
setPINA 0x00
continue 2
expectPORTB 0x0F
expect state R4
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
