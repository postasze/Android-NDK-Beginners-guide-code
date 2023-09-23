package com.packtpub.exception;

public class NotExistingKeyException extends Exception {
    public NotExistingKeyException(String pDetailMessage) {
        super(pDetailMessage);
    }
}
