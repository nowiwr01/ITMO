#!/bin/bash
 
sourcesDir="$HOME/source/"
todayDate=$(date "+%F")
flag=0
backupReport="$HOME/backup-report"
lastbackupDir=$(ls ~/ -1 | grep -E "Backup-[0-9]{4}-[0-9]{2}-[0-9]{2}" | sort -r -k2 | head -1)
if [[ -z $lastbackupDir ]]
then
    lastbackupSec=0
else
    lastbackupSec=$(date --date=$(echo $lastbackupDir | sed "s/^Backup-//") "+%s")
fi
 
let dateDiff=($(date "+%s")\-$lastbackupSec)/60/60/24
if [[ "$dateDiff" -le 7 ]]
then
    currentbackupDir="$HOME/"$lastbackupDir"/"
else
    mkdir "$HOME/Backup-"$todayDate
    currentbackupDir="$HOME/Backup-"$todayDate"/"
    flag=1
fi
 
touch $backupReport
 
if [[ "$flag" == "1" ]]
then
    echo -e "Backup created: "$todayDate"\nWork directory: "$sourcesDir"\nFiles copied:" >> $backupReport
    for file in $(ls $sourcesDir -1)
    do
        cp -r $sourcesDir$file $currentbackDir$file
        echo $file >> $backupReport
    done
else
    echo -e "Update backup: "$currentbackDir"\nDate: "$todayDate >> $backupReport
    for file in $(ls $sourcesDir -1)
    do
        curFile=$currentbackupDir$file
        if [[ -f $curFile ]]
        then
            if [[ "$(stat $sourcesDir$file -c %s)" != "$(stat $curFile -c %s)" ]]
            then
                line=""
                while [[ -f $curFile$line ]]
                do
                    line=$line"."$todayDate
                done
 
                mv $curFile $curFile$line
                cp -r $sourcesDir$file $curFile
                echo -e "Add new version of file "$file" found.\nOld version moved: "$file"."$todayDate >> $backupReport
            fi
        else
            cp -r $sourcesDir$file $curFile
            echo "Add new file "$file >> $backupReport
        fi
    done

    fi

