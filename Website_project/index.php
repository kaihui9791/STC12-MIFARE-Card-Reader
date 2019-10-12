<!DOCTYPE html>

<html>

<head>

<meta charset="utf-8"/>

<title>卡片在线数据库</title>

<style type="text/css">
.tftable {font-size:12px;color:#333333;width:100%;border-width: 1px;border-color: #ebab3a;border-collapse: collapse;}
.tftable th {font-size:12px;background-color:#e6983b;border-width: 1px;padding: 8px;border-style: solid;border-color: #ebab3a;text-align:left;}
.tftable tr {background-color:#ffffff;}
.tftable td {font-size:12px;border-width: 1px;padding: 8px;border-style: solid;border-color: #ebab3a;}
.tftable tr:hover {background-color:#ffff99;}


.cut_str{

/*设置文本为单行，如果超出长度用省略号代替*/

                width: 200px;

                overflow: hidden;/*隐藏超出单元格的部分*/

                text-overflow: ellipsis;/*将被隐藏的那部分用省略号代替。*/

                -o-text-overflow: ellipsis;

                -webkit-text-overflow: ellipsis;

                -moz-text-overflow: ellipsis;

              white-space: nowrap;  /*规定段落中的文本不进行换行*/

}

</style>

</head>

<body>

<table class="tftable" border="1">

<tr><th>编号</th><th>UID</th><th class="cut_str">时间</th><th>数据1</th><th>数据2</th><th>数据3</th><th>空置</th><th>空置</th><th>空置</th></tr>

<?php

session_start();

$servername = localhost;

$username = root;

$password = zuosong114;

$dbname = TEST;

// 创建连接

$conn = mysqli_connect($servername, $username, $password, $dbname);

// Check connection

if (!$conn) {

die("连接失败: " . mysqli_connect_error());

}

$sql = "SELECT Number,UID,time,Data1,Data2,Data3 FROM Test";

$conn->set_charset("utf8"); ////设置编码

$result = mysqli_query($conn, $sql);

if(mysqli_num_rows($result) > 0){

$ant = mysqli_num_rows($result);

while($row = mysqli_fetch_assoc($result)) {

$_SESSION["temp"][$ant]=$row;

//var_dump($_SESSION["temp"][$ant]);

echo "<tr><td>".$row["Number"]."</td><td>".$row["UID"]."</td><td class='cut_str' id='cut_str'>".$row["time"]."</td><td>".$row["Data1"]."</td><td class='cut_str' id='cut_str'>".$row["Data2"]."</td><td>".$row["Data3"]."</td><td>".$row["0"]."</td><td>".$row["0"]."</td><td>".$row["0"]."</td></tr>";

$ant--;

}

mysqli_free_result($result);//释放资源

mysqli_close($conn);

}

?>

</table>

</body>

</html>