<html>
<body>



<?php 

$cmd = './addauthor -r ' . $_POST['author'] . ' *' . $_POST['streams'];
exec($cmd, $output, $status);

if ($status) {
	echo 'addauthor failed';
}
else {
	echo 'Removed: '. $_POST['author'];
	echo ' from: '. $_POST['streams'];
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
