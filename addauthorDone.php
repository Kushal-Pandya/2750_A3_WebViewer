<html>
<body>



<?php 

$cmd = './addauthor ' . $_POST['author'] . ' *' . $_POST['streams'];
exec($cmd, $output, $status);

if ($status) {
	echo 'addauthor failed';
}
else {
	echo 'Added: '. $_POST['author'];
	echo ' to: '. $_POST['streams'];
}


$cmd = './a3 backToMenu.wpml';
exec($cmd, $output, $status);

if ($status)
	echo 'exec failed';
else {
	foreach ($output as $line) {
		echo $line;
	}
}

?>


</body>
</html> 
