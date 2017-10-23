<?php
#------------------------------------------------------------
/**
 * ���������� ����� dmoz
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
	echo "���������� ��������\n";
	connectDataBase();
	selectDataBase();
	$Parser = new TParser($FILENAME);
	$Parser->Start();
	disconnectDataBase();
	echo "���������� ������� �����������\n";
}
catch (Exception $e)
{
	echo "����������!!!\n" . $e->getMessage() . '('. $e->getCode() . ')' . "\n";
	echo "���������� ��������������...";
}
//-----------------------------------------------------------
?>