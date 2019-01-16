if [ "$1" = "-m" ]; then
    # マニュアル

    echo "\n--------------------------------------------------------------"
    echo "== 使用方法 =="
    echo "提出プログラムが置いてあるディレクトリで下記コマンドを実行。"
    echo "$ sh スクリプトのパス/imgSys_CheckAns.sh"
    echo "\n\n== 必要なファイル =="
    echo "- 用意されたファイル一式"
    echo "- 作成したプログラム(名前は「no課題番号.c」)"
    echo "--------------------------------------------------------------"

else
    # コンパイルー＞画像生成ー＞回答比較ー＞提出用スクリプト起動
    echo -n "\n課題番号: "
    read qNum
    echo -n "\nNameOption: "
    read NameOption
    #example r,d,s
    echo -n "\nNumber: "
    read qSecNum
    #example want no13-r2 should type 13 -r 2

    # コンパイル
    # command="gcc -lm -o exe /home/class/j5/imageSystem/sample/bmpfile550.o
    command="gcc -lm -o exe bmpfile550.o no${qNum}-${NameOption}.c"
    #command="gcc -lm -o exe bmpfile550.o cpbmp.c"
    eval $command

    # 画像生成
    command="./exe in${qNum}.bmp in${qNum}-${qSecNum}t.bmp
             ans${qNum}-${qSecNum}${NameOption}.bmp"
    eval $command

    # 回答比較
    command="/home/class/j5/imageSystem/bin/diffbmp ans${qNum}-${qSecNum}${NameOption}.bmp
            out${qNum}-${qSecNum}${NameOption}.bmp"
    eval $command

    #echo -n "\n提出 > Enter"
    #read dummy

    # 提出用スクリプト起動
    #command="sh /home/class/j5/imageSystem/bin/send5.sh"
    #eval $command
fi
