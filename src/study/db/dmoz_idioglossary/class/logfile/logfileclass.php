<?php
//------------------------------------------------------------
require_once('logfiledefine.php');
//------------------------------------------------------------
/**
 * Операции с лог файлом
 *
 * 
 */

class TLogFile
{
	private $FilePointer = null;
	//private $LogFileName = "";
	
	/**
	 * Open log file
	 *
	 * @param unknown_type $name
	 */
	public function __construct($name = "")
	{
		if ((string) $name == "")
		{
			//$LogFileName = DEFAULTLOGFILENAME;
			$name = DEFAULTLOGFILENAME;
		}		
		if ($this->FilePointer = fopen($name, 'a'))
		{
			$this->Write(sprintf("%s\n%s\n", date("F j, Y, H:i"), BREAKLOGFILE));
			//$this->Write();
		}
		else 
		{
			throw new Exception(OPENLOGEERROR . $name, 0);
		}
	}
	
	/**
	 * Close log file
	 *
	 */
	public function __destruct()
	{
		$this->Write(BREAKLOGFILE . "\n\n");
		fclose($this->FilePointer);
	}
	
	/**
	 * Write to log file
	 *
	 * @param string $string
	 * @return int
	 */
	public function Write($string)
	{
		$numberofbyteswritten = fwrite($this->FilePointer, $string, strlen($string));
		if ($numberofbyteswritten === false)
		{
			throw new Exception(WRITELOGERROR, 0);
		}
		return $numberofbyteswritten;
	}
}
?>