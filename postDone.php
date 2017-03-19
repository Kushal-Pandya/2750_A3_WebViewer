<html>
<body>



<?php 

$cmd = './post ' . $_POST['author'] . ' *' . $_POST['stream'] . ' @"' . $_POST['text'] . '"';
exec($cmd, $output, $status);

if ($status) {
	echo 'post failed';
}
else {
	echo '<h5>Added Post<h5> from: '. $_POST['author'];
	echo ' to: '. $_POST['stream'];
	echo '<br>';
	echo 'Text: ' . $_POST['text']; 
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
