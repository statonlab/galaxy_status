<?php
/**
 * @return array
 */
function galaxy_status_drush_command()
{
    $commands = [];

    $commands['galaxy-check'] = [
        'description' => 'Send an email to admins about the status of galaxy instances.',
        'options' => [
            'emails' => 'Comma separated list of emails',
        ],
    ];

    return $commands;
}

/**
 * @throws \Exception
 */
function drush_galaxy_status_galaxy_check()
{
    $emails = drush_get_option('emails', null);

    if (is_null($emails)) {
        throw new Exception('Please provide emails to send the report to.');
    }

    $emails = explode(',', $emails);

    foreach ($emails as &$email) {
        $email = trim($email);

        if (! filter_var($email, FILTER_VALIDATE_EMAIL)) {
            throw new Exception("$email is not a valid email.");
        }
    }

    galaxy_status_perform_checks($emails);
}
