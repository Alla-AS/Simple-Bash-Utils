ды#!/bin/bash

COUNTER=0
COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="cat_test.txt"
echo "" > log.txt

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
done

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
        fi
  done
done

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
      for var3 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="$var $var2 $var3 $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt

        fi
      done
  done
done

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
      for var3 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
      do
          for var4 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              TEST1="$var $var2 $var3 $var4 $TEST_FILE"
              echo "$TEST1"
              ./s21_cat $TEST1 > s21_cat.txt
              cat $TEST1 > cat.txt
              DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
              (( COUNTER++ ))
              if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
                then
                  (( COUNTER_SUCCESS++ ))
                  echo -e "$COUNTER TEST STATUS: \033[32mSUCCESS\033[0m"
                else
                  echo "$TEST1" >> log.txt
                  (( COUNTER_FAIL++ ))
              fi
              rm s21_cat.txt cat.txt

            fi
          done
      done
  done
done

echo -e "\033[32mNUMBER OF SUCCESS TESTS: $COUNTER_SUCCESS\033[0m"
echo "NUMBER OF FAILED TESTS: $COUNTER_FAIL"
