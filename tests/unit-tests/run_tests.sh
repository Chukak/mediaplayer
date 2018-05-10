#! /bin/bash

PATH_TESTING=$(pwd)
TEST_DIRS=(MediaPlayer VideoOutput SubtitlesOutput SubtitleParser)
declare -A TEST_FILES
TEST_FILES=([MediaPlayer]=tst_mediaplayertest [VideoOutput]=tst_videooutputtest [SubtitlesOutput]=tst_subtitlesoutputtest [SubtitleParser]=tst_subtitleparsertest)

for test_dir in ${TEST_DIRS[@]}; do
    if [[ -d $PATH_TESTING/$test_dir ]]; then
        if [[ -f $PATH_TESTING/$test_dir/${TEST_FILES[$test_dir]} ]]; then
            cd $PATH_TESTING/$test_dir/
            ./${TEST_FILES[$test_dir]}
        else 
            echo "A file ${TEST_FILES[$test_dir]} not found."
        fi
    else
        echo "A directory $PATH_TESTING/$test_dir/ not found."
    fi
done

unset TEST_FILES
unset TEST_DIRS
unset PATH_TESTING
