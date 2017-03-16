<html>
<body>

<?php 

$cmd = './a3 post.wpml';
exec($cmd, $output, $status);

if ($status)
	echo 'exec failed';
else {
	foreach ($output as $line) {
		echo $line;
	}
}

?>

Authors:
<?php 
	echo $_POST["author"]; 
?>
<br>
Streams: 
<?php 
	echo $_POST["streams"]; 
?>

</body>
</html> 
