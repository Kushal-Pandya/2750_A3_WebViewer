<html>
<body>

<?php 

$cmd = './a3 view.wpml';
exec($cmd, $output, $status);

if ($status)
	echo 'exec failed';
else {
	foreach ($output as $line) {
		echo $line;
	}
}

session_start();
echo 'AUTHOR: ' . $_SESSION['author'];

?>

</body>
</html> 