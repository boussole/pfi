<?php
#------------------------------------------------------------
/**
 * Парсировка сайта dmoz
 * 
 */
#------------------------------------------------------------
//include (require)
require_once('./db/dmozdatabase.php');
require_once('./class/parserclass.php');
#------------------------------------------------------------
# Variables
$FILENAME		= 'test.xml';
//-----------------------------------------------------------
try
{
	echo "Парсировка началась\n";
	connectDataBase();
	selectDataBase();
	$Parser = new TParser($FILENAME);
	$Parser->Start();
	disconnectDataBase();
	echo "Парсировка успешно завершилась\n";
}
catch (Exception $e)
{
	echo "Исключение!!!\n" . $e->getMessage() . '('. $e->getCode() . ')' . "\n";
	echo "Парсировка приостановлена...";
}
//-----------------------------------------------------------
?>