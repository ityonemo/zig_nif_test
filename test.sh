#!/bin/sh

rm priv/nif/*
MIX_ENV=test mix clean
mix test
