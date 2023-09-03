#!/bin/bash

COUNTER=0
COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
echo "" > log.txt

for var in -v -c -l -n -h -o
do
  for var2 in -v -c -l -n -h -o
  do
      for var3 in -v -c -l -n -h -o
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="for s21_grep.c $var $var2 $var3"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST2="for s21_grep.c $var $var2 $var3"
          echo "$TEST2"
          ./s21_grep $TEST2 > s21_grep.txt
          grep $TEST2 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
            else
              echo "$TEST2" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST3="-e for -e ^int s21_grep.c $var $var2 $var3"
          echo "$TEST3"
          ./s21_grep $TEST3 > s21_grep.txt
          grep $TEST3 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
            else
              echo "$TEST3" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST4="-e for -e ^int s21_grep.c $var $var2 $var3"
          echo "$TEST4"
          ./s21_grep $TEST4 > s21_grep.txt
          grep $TEST4 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
            else
              echo "$TEST4" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST5="-e regex -e ^print s21_grep.c $var $var2 $var3 -f grep_test_pattern.txt"
          echo "$TEST5"
          ./s21_grep $TEST5 > s21_grep.txt
          grep $TEST5 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
            else
              echo "$TEST5" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST6="-e while -e void s21_grep.c $var $var2 $var3 -f grep_test_pattern.txt"
          echo "$TEST6"
          ./s21_grep $TEST6 > s21_grep.txt
          grep $TEST6 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
            else
              echo "$TEST6" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

        fi
      done
  done
done

echo -e "\033[32mNUMBER OF SUCCESS TESTS: $COUNTER_SUCCESS\033[0m"
echo "NUMBER OF FAILED TESTS: $COUNTER_FAIL"