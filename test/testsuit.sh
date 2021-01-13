#!/usr/bin/bash

TEST_DIRS=(simple)

red="\e[31m"
green="\e[32m"
default="\e[39m"
for test_dir in ${TEST_DIRS[@]}; do
    list_dir=$(ls $test_dir)
    for _test in $list_dir; do
        export MULTICONF=$(cat $test_dir/$_test/env)
        multiconf -i "$test_dir/$_test/test" -o  "$test_dir/$_test/out"
        if diff "$test_dir/$_test/expected" "$test_dir/$_test/out"; then
            echo -e "$green$test_dir/$_test$default"
        else
            echo -e "$red$test_dir/$_test$default"
        fi

    done
done

