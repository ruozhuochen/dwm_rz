#!/usr/bin/php
<?php

    #// See http://php.net/manual/function.imap-open.php for more information about
#// the mailbox string in the first parameter of imap_open.
#// This example is ready to use with Office 365 Exchange Mails,
#// just replace your username (=email address) and the password.
# Require you install php5-cli , php5-imap and do php5enmod
# sudo apt-get install php5-cli php5-imap
# sudo php5enmod imap
function checkEmails()
{
    $properties = parse_ini_file("/home/rchen/.config/office365.ini");
    $mbox = imap_open($properties['host'], $properties['user'], $properties['pass']);

    if (!$mbox) {
        $message = sprintf("The login details you provided:\nUsername: %s\nPassword: %s\nDoes NOT work for %s",  $properties['user'], $properties['pass'], $properties['host']);
        $cmd = sprintf('echo "%s" | xmessage -timeout 15 -file -', $message);
        shell_exec($cmd);
        return;
    }

    $unseen = imap_search($mbox, 'UNSEEN');
    $nrUnseen = $unseen ? count($unseen) : 0;
    //$message = 'echo "You have >> %d << unread messages in your account.\n\n%s" | xmessage -timeout 15 -file -'; 
    //$message = 'notify-send "New Message" "You have %d unread messages in your account.\n%s" -i email -t 23000'; 
    $notifyMessage = 'notify-send "%s" "%s" -i email -t 10000 &';
    $newMessage = 'You have %d unread messages in your account.'; 
    $fromMessage = 'From: %s';
    $subjectMessage = '[%s] Subject: %s';

    if ($nrUnseen > 0) {
        $newEmailNote = sprintf($newMessage, $nrUnseen);
        shell_exec(sprintf($notifyMessage, "New Emails", $newEmailNote));
        foreach ($unseen as $uid) {
            $email = imap_headerinfo($mbox, $uid);
            $fromAddress = $email->fromaddress;
            $date = $email->date;
            $subject = $email->subject;
            $fromNote = str_replace("\"", "", sprintf($fromMessage, $fromAddress));
            $subjectNote = str_replace("\"", "", sprintf($subjectMessage, $date, $subject));
            shell_exec(sprintf($notifyMessage, $fromNote, $subjectNote));
        }
    }
    imap_close($mbox);
}

while (true) {
    checkEmails();
    sleep(300);
}
?>
